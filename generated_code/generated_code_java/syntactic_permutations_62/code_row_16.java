import java.util.*;

public class CheckSum {
    public static void main(String[] args) throws Exception {
        FileInputStream in = null;
        DataInputStream input = null;
        int sum = 0;
        byte[] buffer;
        try {
            in = new FileInputStream("C:\\Users\\User\\Desktop\\test.txt");
            input = new DataInputStream(in);
            buffer = new byte[input.available()];
            input.readFully(buffer);
            for (byte a : buffer)
                sum += a;
        } finally {
            if (in != null)
                in.close();
        }

        FileOutputStream out = null;
        DataOutputStream output = null;

        try {
            out = new FileOutputStream("C:\\Users\\User\\Desktop\\result.txt");
            output = new DataOutputStream(out);
            output.writeInt(buffer.length);
            output.writeInt(sum);
        } finally {
            if (in != null)
                in.close();
        }
    }
}