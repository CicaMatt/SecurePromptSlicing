import java.io.*;

public class Main {

    public static void main(String[] args) throws IOException {
        
        File file = new File("important_config");
        open(file, "w", 0754);
        write("important_config\n", 1);
    }

    private static int open(File file, String w, int mode) throws IOException {
        OutputStreamWriter osw = new OutputStreamWriter(new FileOutputStream(file));
        osw.write("important_config");
        return 0;
    } 
}