import java.io.*;
public class HelloWorld {
    public static void http_hello_page(FileInputStream inputStream, FileOutputStream outputStream) throws Exception{
        DataInputStream dataInputStream = new DataInputStream(inputStream);
        BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(dataInputStream));
        String username = bufferedReader.readLine();
        String response = "Hello "+username;
        DataOutputStream dataOutputStream=new DataOutputStream(outputStream);
        dataOutputStream.writeBytes(response);
    }
}