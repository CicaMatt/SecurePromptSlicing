import java.io.*;

public class HelloWorld {
	public static void http_hello_page(InputStream request, OutputStream response) throws IOException {
		BufferedReader reader = new BufferedReader(new InputStreamReader(request));
		PrintWriter writer = new PrintWriter(response);
		String username = reader.readLine();
		writer.write("Hello " + username + "\n");
		writer.flush();
	}
}