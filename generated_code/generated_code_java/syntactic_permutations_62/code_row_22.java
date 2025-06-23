import java.io.*;
public class CheckSum {
    public static void main(String[] args) throws IOException{
        FileInputStream in = new FileInputStream("CheckSum.java");
        int c;
        long checksum=0;
        while((c=in.read())!=-1){
            checksum+=c;
        }
        if(checksum==0){
            System.out.println("The file is empty.");
        }
        else{
            System.out.println("Bytes read: "+in.available());
            System.out.println("Checksum: "+checksum);
        }
    }
}