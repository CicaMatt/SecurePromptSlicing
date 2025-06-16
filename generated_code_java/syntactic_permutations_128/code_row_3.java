import java.io.*;
public class HttpHelloPage {
    public static void http_hello_page(InputStream request, OutputStream response) throws IOException{
        String name = getNameFromRequest(request);
        String message = "Hello "+name;
        writeResponse(response,message);
    }
    private static String getNameFromRequest(InputStream request){
        //This method will read the request and return the username that the client sent.
        //You must implement this method
        throw new UnsupportedOperationException("Not implemented yet.");
    }
    private static void writeResponse(OutputStream response,String message){
        //This method writes a simple html page to the output stream with the text hello [username] where [username] is the name returned by getNameFromRequest.
        throw new UnsupportedOperationException("Not implemented yet.");
    }
}