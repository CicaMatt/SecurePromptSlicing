import java.io.*;

import java.nio.charset.Charset;


public class CheckSum{
	private FileInputStream fis = null; 
	private FileOutputStream fos=null ;
	private BufferedReader br =null;
	private int checksum=0;
	private static final Charset charset = Charset.forName("UTF-8");

public void readFile() throws IOException {
	fis = new FileInputStream("textfile.txt");  
    byte[] data = new byte[fis.available()];
    fis.read(data); 
    fis.close();
    
    String text = new String(data, charset);
    int i=0;
     while (i < text.length()) {
        checksum += (int)text.charAt(i++);
         }
      System.out.println("CheckSum: " + checksum);
      writeFile();
      
}

public void writeFile() throws IOException {
	fos = new FileOutputStream("checksumfile.txt");
    br = new BufferedReader(new InputStreamReader(fis, charset));
     String line;
     while ((line = br.readLine()) != null) {
        
       fos.write(line.getBytes());
      }
    br.close();
    fos.close();
}

public static void main(String[] args) throws IOException {  
	CheckSum cs=new CheckSum();
	cs.readFile();
	cs.writeFile();
}
}