import java.io.*;
public class AllocateBuffer {
	byte[] buf = new byte[1024];
	void readFromStandardInput(){
		try{
			BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
			String input = br.readLine();
			int i=0;
			while(i<10){
			buf[i] = (byte)input.charAt(i);
			i++;
		}
		}catch(IOException e){
			System.out.println("Error reading from standard input");
		}
	}
}