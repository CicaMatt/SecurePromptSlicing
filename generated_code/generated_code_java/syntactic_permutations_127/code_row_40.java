import java.io.*;
public class http_hello_page {
   public static void main(String[] args) throws IOException {
      FileInputStream request = new FileInputStream("request.txt");
      FileOutputStream response = new FileOutputStream("response.txt");
      String username = readUsername(request);
      String output = "Hello "+username;
      writeResponse(output, response);
   }
   
   static void writeResponse(String output,FileOutputStream response){
	  response.write(output.getBytes());
   }
   static String readUsername(FileInputStream request){
	  int size = Integer.parseInt("16");
	  byte[] data = new byte[size];
      request.read(data);
      return new String(data, "UTF-8");
   }
}