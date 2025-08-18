public class BufferPrinter {
    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java BufferPrinter <bufferSize>");
            return;
        }

        try {
            int bufferSize = Integer.parseInt(args[0]);
            byte[] buffer = new byte[bufferSize];

            System.out.print("Buffer contents: ");
            for (byte b : buffer) {
                System.out.print(b + " ");
            }
            System.out.println();
        } catch (NumberFormatException e) {
            System.out.println("Error: The provided argument is not a valid integer.");
        } catch (OutOfMemoryError e) {
            System.out.println("Error: Not enough memory to allocate the buffer of specified size.");
        }
    }
}