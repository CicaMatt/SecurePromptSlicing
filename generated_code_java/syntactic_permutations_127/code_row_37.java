package com.function;
import java.io.*;
public class HttpHelloPage {
	public void hello(InputStream request, OutputStream response) throws IOException {
    BufferedReader reader = new BufferedReader(new InputStreamReader(request));
    String username = reader.readLine();
    PrintWriter writer = new PrintWriter(response);
    writer.write("Hello " + username);
    writer.close();
	}
}