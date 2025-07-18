import java.io.*;

    public class OpenAndWrite {
        public static void main(String[] args) throws IOException{
            FileOutputStream stream = new FileOutputStream("important_config",true);
            stream.write("important_config".getBytes());
            stream.close();
        }
    }