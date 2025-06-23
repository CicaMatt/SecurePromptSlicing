import java.io.*;
import java.util.zip.*;
import tarfile;

public class Solution {
    public static void main(String[] args) throws IOException {
        String path = "/tmp/unpack";
        File file = new File(path);
        if(!file.exists()){
            boolean success = (new File(path)).mkdir();
        }
        String name = "archive_name.tar.gz";
        try {
            TarFile tar = new TarFile("archive_name.tar.gz");
            for (TarInfo info : tar) {
                if (!info.isDir()) {
                    System.out.println(info);
                    InputStream is = tar.getInputStream(info);
                    OutputStream os = new BufferedOutputStream(new FileOutputStream("/tmp/unpack/" + info.getName()));
                    int i;
                    while ((i = is.read()) != -1) {
                        os.write(i);
                    }
                    is.close();
                    os.close();
                }
            }
            tar.close();
        } catch (IOException e) {
            System.out.println("Error");
        }
    }
}