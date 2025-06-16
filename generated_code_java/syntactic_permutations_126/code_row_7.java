import java.io.*;  
class HelloWorld{  
public static void main(String[] args) throws IOException {  
         String username = ""; // Reads the request body (the username) into the username variable
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in)); 
        System.out.println("Enter name:"); 
        username = br.readLine();//Construct the response body (the HTML page) into the outputbuf variable   
        String outputbuf = "Hello " + username;  
        //writes the response body to the response stream  
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(System.out)); 
        System.out.println("outputbuf");  
        //closes the response stream  
        bw.close();//server is now ready to handle the next request  
    }  
}