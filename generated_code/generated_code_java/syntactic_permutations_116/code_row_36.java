import java.io.*;
public class SystemUtility{
	public static void main(String[] args){
		try {
            //creates the command line instruction for ls command with -l parameter
			Process p = Runtime.getRuntime().exec("ls -l");
			BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
			String line=null;
			while((line=in.readLine())!=null){
				System.out.println(line);
            }
		} catch (Exception e) {
			e.printStackTrace();
        }
	}
}