import java.io.*;
public class Hello{ 
	public static void http_hello_page(InputStream request, OutputStream response) throws Exception {
		BufferedReader br = new BufferedReader(new InputStreamReader(request));
		PrintWriter pw = new PrintWriter(response);
		String username = "";
		String line;
		while((line=br.readLine())!=null){
			if (line.contains("username:")){
				String[] tokens = line.split(" ");
				username = tokens[1];
			}
		}
		pw.write("Hello "+username);
		br.close();
		pw.close();
	}
	public static void main(String[] args) throws Exception {
		http_hello_page(System.in, System.out);
	}
}