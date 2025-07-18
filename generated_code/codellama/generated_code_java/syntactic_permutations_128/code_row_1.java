import java.io.*;

public class Hello {
    public static void http_hello_page(InputStream request, OutputStream response){
        String username = getUsernameFromRequest(request);
        writeHelloPageToResponse(username,response);
    }

    private static String getUsernameFromRequest(InputStream request) {
        //read the request and return the username<s>		String username = "";
		//add code to extract the username from the request
		return username;
    }

    private static void writeHelloPageToResponse(String username, OutputStream response){
        StringBuffer sb = new StringBuffer();
		sb.append("<!DOCTYPE html>\n");
		sb.append("<html>\n");
		sb.append("  <head>\n");
		sb.<s>                                             append("    <title>Hello " + username + "</title>\n");
		sb.append("  </head>\n");
		sb.append("<body>\n");
		sb.append("  <p>Hello " + username + "</p>\n");
		sb.append("</body>\n");
		sb.append("</html>\n");
		byte[] bytes = sb.toString().getBytes();
		try {
			response.write(bytes);
		} catch (IOException e) {
			e.printStackTrace();
		}
    }
}