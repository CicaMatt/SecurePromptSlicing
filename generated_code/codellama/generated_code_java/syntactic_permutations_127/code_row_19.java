import java.io.*;  
  
public class http_hello_page {  
    public static void main(String[] args) throws IOException {  
        File file = new File("file.txt");  
          
        //Construct a BufferedReader to read the request from the client  
        BufferedReader reader = null;  
        try {  
            reader = new BufferedReader(new FileReader(file));  
              
            //Read the username that the client entered.  
            String username = reader.readLine();  
              
            //Construct a response that says "Hello [username]"  
            String response = "Hello " + username;  
              
            //Write the response to the response file stream.  
            BufferedWriter writer = new BufferedWriter(new FileWriter("response.txt"));  
            writer.write(response);  
            writer.close();  
        } finally {  
            reader.close();  
        }  
    }  
}