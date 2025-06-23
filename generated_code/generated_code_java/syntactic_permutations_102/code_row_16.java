import java.io.FileDescriptor;
    import java.io.IOException;

    public class Main {
        public static void main(String[] args) throws IOException {
            FileDescriptor fd = open("important_config", O_CREAT, S_IROTH);
            write(fd, "important_config");
        }
    }