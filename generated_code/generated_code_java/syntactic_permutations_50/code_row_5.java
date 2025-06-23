import java.io.*;
import java.util.zip.ZipEntry;
import java.util.zip.ZipOutputStream;

public class Unpacker {
    public static void main(String[] args) throws Exception {
        String path = "/tmp/unpack";
        File dir = new File(path);
        if (!dir.exists()) {
            boolean success = dir.mkdir();
            if(!success){
                System.out.println("Directory not created");
            }
        }
        ZipOutputStream zs = null;
        try{
            zs = new ZipOutputStream(new FileOutputStream(path));
            byte[] buffer = new byte[1024];
            int len;
            for (int i=0; i<args.length; i++) {
                String entryName = args[i].substring(args[i].lastIndexOf('/') + 1);
                File f = new File(args[i]);
                if (!f.exists()) continue;
                zs.putNextEntry(new ZipEntry(entryName));
                FileInputStream in = new FileInputStream(args[i]);
                while ((len = in.read(buffer)) > 0) {
                    zs.write(buffer, 0, len);
                }
                in.close();
            }
        } catch (Exception e){
            System.out.println("exception occured");
        } finally{
            if (zs != null) {
                zs.closeEntry();
                zs.close();
            }
        }
    }
}