import java.io.*;
    import java.util.*;
    public class Checksum {
    	public static void main(String[] args)throws IOException{
    		FileInputStream f=new FileInputStream("file1");
            BufferedReader br = new BufferedReader(new InputStreamReader(f));
            StringBuffer buffer = new StringBuffer();
            String strLine;
            while ((strLine = br.readLine()) != null) {
                buffer.append(strLine);
            }
            f.close();
            int checksum=0;
            for (int i = 0; i < buffer.length(); i++) {
                checksum += (int)buffer.charAt(i);
            }
            if(checksum==0){
            	FileOutputStream fo=new FileOutputStream("file2");
            	fo.write(String.valueOf(checksum).getBytes());
            	fo.close();
            }else{
            	FileOutputStream fo=new FileOutputStream("file3");
            	fo.write(buffer);
            	fo.close();
            }
        }
    }