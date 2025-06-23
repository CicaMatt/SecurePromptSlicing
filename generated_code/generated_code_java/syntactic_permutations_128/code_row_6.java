import java.io.*;
class http_hello_page {
	public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
		OutputStreamWriter writer = new OutputStreamWriter(System.out);
		int ch;
		StringBuffer sb = new StringBuffer();
		while ((ch = reader.read()) != -1) {
			sb.append((char) ch);
		}
		writer.write("HTTP/1.0 200 OK\r\n");
		writer.write("\r\n");
		writer.write("<html><body>hello " + sb.toString() + "</body></html>\r\n");
	}
}