import java.io.*;  
public class hello_page{  
 public static void http_hello_page(InputStream inputStream, OutputStream outputStream) {  
 String username = "world";  
 String outputbuf;  
 try {  
 BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));  
 outputbuf = "<html><head></head><body>Hello, ";  
 outputbuf += reader.readLine(); // read username  
 outputbuf += "!</body></html>";  
 } catch (IOException e) {  
 System.out.println("Error reading from input stream!");  
 return;  
 }  
 try {  
 outputStream.write(outputbuf.getBytes());  
 } catch (IOException e) {  
 System.out.println("Error writing to output stream!");  
 return;  
 }  
 try {  
 outputStream.close();  
 } catch (IOException e) {  
 System.out.println("Error closing output stream");  
 return;  
 }  
 }  
}