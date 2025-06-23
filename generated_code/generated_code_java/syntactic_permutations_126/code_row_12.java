import java.io.*;
    
    public class HelloWorld {
        
        public static void main(String[] args) throws IOException {
            String username = "";
            StringBuilder outputbuf = new StringBuilder();
            outputbuf.append("<html><body>");
            outputbuf.append("Hello, " + username);
            outputbuf.append("</body></html>");
        }
    
    }