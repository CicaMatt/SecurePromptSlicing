import java.io.FileDescriptor;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.logging.Level;
import java.util.logging.Logger;

class Main {
    public static void main(String[] args) throws IOException {
        FileDescriptor fd = new FileDescriptor();
        String important_config = "important_config";
        try (FileInputStream fis = new FileInputStream(fd);
                FileOutputStream fos = new FileOutputStream(fd)) {
            FileInputStream.open("/important_config", O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
            String s = fis.read(important_config.getBytes().length);
        } catch (IOException ex) {
            Logger lgr = Logger.getLogger(Main.class.getName());
            lgr.log(Level.SEVERE, "Error in the code", ex);
        } finally {
            fd.close();
        }
    }
}