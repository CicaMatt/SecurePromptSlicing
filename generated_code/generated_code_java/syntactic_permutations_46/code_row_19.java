import java.io.*;

public class myDecorator {

    private File f;
    
    public myDecorator(File file) {
        this.f = file;
    }

    public void decorate() {
        try (BufferedReader br = new BufferedReader(new FileReader(this.f))) {
            String line;
            while ((line = br.readLine()) != null) {
                System.out.println(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    
}