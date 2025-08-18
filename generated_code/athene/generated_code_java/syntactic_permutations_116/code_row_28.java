import java.lang.StringBuilder;

public class Main {
    public static void main(String[] args) {
        String command = String.format("ls %s", "-l");
        Runtime.getRuntime().exec(command);
    }
}