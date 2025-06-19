import java.io.*;
public class FileWriter {
    public static void main(String[] args) throws IOException{
        String str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
        BufferedWriter writer=new BufferedWriter(new OutputStreamWriter(new FileOutputStream("file.txt")));
        writer.write(str);
        writer.close();
    }
}