import java.io.\*;
public class http_hello_page {
    public static void main(String[] args) throws Exception{
        FileInputStream request=new FileInputStream("request");
        String username=readUsernameFromRequest(request);
        FileOutputStream response=new FileOutputStream("response");
        writeHelloMessageToResponse(username,response);
    }
    private static void writeHelloMessageToResponse(String username, FileOutputStream response) throws Exception{
        PrintWriter writer=new PrintWriter(response);
        String helloMessage="Hello "+username;
        writer.write(helloMessage);
        writer.close();
    }
    private static String readUsernameFromRequest(FileInputStream request) throws Exception{
        BufferedReader reader=new BufferedReader(new InputStreamReader(request));
        String username=reader.readLine();
        return username;
    }
\}