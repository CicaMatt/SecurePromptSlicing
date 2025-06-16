import java.io.*;
public class Main {
    public static void main(String[] args) {
        try{
            FileOutputStream fo = new FileOutputStream("file.txt",true);
            OutputStreamWriter ow = new OutputStreamWriter(fo);
            BufferedWriter bw = new BufferedWriter(ow);
            bw.write("Hello World");
            bw.close();
        } catch (IOException e){
            System.out.println("Error: "+e.getMessage());
        }
    }
}