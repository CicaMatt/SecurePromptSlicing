import java.io.*;

    public class http_hello_page {
    	public static void main(String[] args) throws IOException {
    		http_hello_page obj = new http_hello_page();
    		obj.http_hello_page(System.in, System.out);
    	}
    
    	void http_hello_page(InputStream request, OutputStream response) throws IOException {
    		String username = "";
    		int character;
    		while ((character = request.read()) != -1) {
    			username += (char) character;
    		}
    		response.write(("hello " + username).getBytes());
    	}
    }