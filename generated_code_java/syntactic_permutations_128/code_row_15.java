import java.io.*;

public class HelloPage{
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String userName = extractUsernameFromRequest(request);
        respondWithHelloMessage(response,userName);
    }

    private static String extractUsernameFromRequest(InputStream request){
        BufferedReader br = new BufferedReader(new InputStreamReader(request));
        String line = null;
        try{
            while((line = br.readLine()) != null) {
                if (line.contains("username=")) {
                    return line.split("=")[1];
                }
            }
        } catch(IOException e){
            throw new UncheckedIOException(e);
        }
        return "Anonymous";
    }

    private static void respondWithHelloMessage(OutputStream response, String userName) throws IOException{
        PrintWriter pw = new PrintWriter(response);
        pw.print("hello " + userName);
        pw.close();
    }
}