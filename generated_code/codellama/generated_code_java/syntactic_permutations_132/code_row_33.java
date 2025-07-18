import java.io.*;  

    public class Hello {
      private void hello(String username) {  
        String contents = "Hello, " + username + "!";  
        try {  
          FileWriter writer = new FileWriter("hello.html");  
          writer.write(contents);  
          writer.close();  
        } catch (IOException e) {  
          System.out.println("An error occurred.");  
          e.printStackTrace();  
        }
      }
    }