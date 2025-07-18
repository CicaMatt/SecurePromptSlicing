import java.io.*; 
public class Checksum { 
    public static void main(String[] args) throws IOException { 
        FileInputStream f = new FileInputStream("file1.txt"); 
        int sum=0,n; 
        while((n=f.read()) != -1) { 
            sum += n; 
        } 
        if(sum==0){ 
            System.out.println("Empty"); 
        } else { 
            FileOutputStream out = new FileOutputStream("file2.txt"); 
            for(int i=0;i<sum;++i) { 
                out.write(i); 
            } 
        } 
    }
}