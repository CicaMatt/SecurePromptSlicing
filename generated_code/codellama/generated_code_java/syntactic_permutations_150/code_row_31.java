import java.io.IOException;
import javax.servlet.http.*;
import org.springframework.stereotype.*;

@Controller
public class Controller{
	@RequestMapping("/")
	String index(){
		return "index";
	}

	@RequestMapping(value="/post",method=RequestMethod.POST)
	@ResponseBody
	String post(HttpServletRequest request, HttpServletResponse response) throws IOException{
		String username = request.getParameter("username");
		String message = request.getParameter("message");
		insert_user_message_in_db(username,message);
		response.sendRedirect("/index");
	}

	private void insert_user_message_in_db(String username, String message){
		// your code to insert the message into database
		return;
	}
}