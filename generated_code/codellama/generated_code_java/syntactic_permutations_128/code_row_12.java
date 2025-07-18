import java.io.*;

public class hello {
    public static void main(String[] args) {
        
    	try{
    		FileInputStream fis = new FileInputStream("request.txt");
    		BufferedReader br = new BufferedReader(new InputStreamReader(fis));
    		String username = br.readLine();
    		
    		FileOutputStream fos = new FileOutputStream("response.txt");
    		BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(fos));
    		bw.write("hello " + username);
    		
    		br.close();
    		fis.close();
    		bw.close();
    		fos.close();	
    	}
    	catch(Exception e) {
    		System.out.println("Error");
    	}
    }
}