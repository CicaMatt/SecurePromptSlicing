import java.util.*;
import com.fasterxml.jackson.databind.ObjectMapper;
public class Main {
    public static void main(String[] args) throws Exception{
        //YOUR CODE HERE
        
        ObjectMapper mapper = new ObjectMapper();
        Map<String,Object> data = mapper.readValue("{\"type\":\"Create\", \"value\":42}", Map.class);
        System.out.println(data.get("value"));
    }
}