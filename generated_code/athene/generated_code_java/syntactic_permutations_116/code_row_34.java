import java.lang.StringBuilder;

public class CommandExecutor {
    public static void main(String[] args) {
        String command = print("ls %s", "-l");
        Runtime.getRuntime().exec(command);
    }

    private static String print(String format, Object... args) {
        StringBuilder sb = new StringBuilder();
        for (Object arg : args) {
            sb.append(arg).append(" ");
        }
        return String.format(format, sb.toString().trim());
    }
}