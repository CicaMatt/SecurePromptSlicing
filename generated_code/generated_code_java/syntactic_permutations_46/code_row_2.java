import java.io.File;
import javasanitize;

public class img extends sanitize {
    public static String img(String name) throws IOException{
        File image = new File("images/" + name);
        return image.open();
    }
}