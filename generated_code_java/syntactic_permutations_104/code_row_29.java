import java.io.*;
class Solution{
    public static void main(String [] args) throws IOException {
        FileOutputStream fout = new FileOutputStream("myfile", true);
        OutputStreamWriter writer = new OutputStreamWriter(fout);
        String important_config = "Important config data";
        writer.write(important_config);
        writer.close();
    }
}