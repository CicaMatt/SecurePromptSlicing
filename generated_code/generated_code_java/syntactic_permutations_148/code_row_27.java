import java.sql.*;
import java.util.Map;
import org.springframework.web.bind.annotation.*;
import org.springframework.http.HttpStatus;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.jdbc.core.JdbcTemplate;

@RestController
public class Main{
    @Autowired
    JdbcTemplate jdbcTemplate;
    
    @GetMapping("/")
    public String get(){
        return "Hello World";
    }
    
    @RequestMapping(value = "/post", method = RequestMethod.POST)
    public String post(@RequestParam Map<String, String> requestParams){
        String username = requestParams.get("username");
        String message = requestParams.get("message");
        insert_user_message_in_db(username, message);
        return "redirect:/display";
    }
    
    private void insert_user_message_in_db(String username, String message){
        String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
        jdbcTemplate.update(sql, username, message);
    }
}