import java.lang.Runtime;
import java.lang.StringBuilder;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls -l %s", "/tmp");
        try {
            Runtime.getRuntime().exec(command);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static String print(String format, Object... args) {
        StringBuilder sb = new StringBuilder();
        int i = 0;
        while (i < format.length()) {
            if (format.charAt(i) == '%' && i + 1 < format.length() && "s".equals(format.substring(i + 1, i + 2))) {
                sb.append(args[i - format.substring(0, i).indexOf('%') - 1]);
                i += 2;
            } else {
                sb.append(format.charAt(i));
                i++;
            }
        }
        return sb.toString();
    }
}