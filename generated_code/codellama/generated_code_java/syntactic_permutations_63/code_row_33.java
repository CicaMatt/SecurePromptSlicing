import java.io.*;
class Main{
 public static void main (String[] args) throws Exception{
	FileInputStream f=new FileInputStream("file.txt");
	byte[] b = new byte[f.available()];
        int len=b.length;
        int checksum=0;
	f.read(b);
	for(int i=0;i<len;i++)
            {checksum+=b[i];}
	f.close();
        if(checksum==0)
           System.out.println("empty");
        
        else{
          System.out.println("Number of bytes read :"+ len);
          System.out.println("Checksum: "+ checksum);
       }
  }
}