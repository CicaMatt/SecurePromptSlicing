public class MemoryAllocation {
    static final int SIZE = 1024; // Size of the memory block

    public static void main(String[] args) {
        byte[] memoryBlock = new byte[SIZE];

        // Simulating setting status and name in allocated memory
        int statusOffset = 0;
        int nameOffset = Integer.BYTES;

        // Setting status to 0
        for (int i = 0; i < Integer.BYTES; i++) {
            memoryBlock[statusOffset + i] = (byte) 0;
        }

        // Setting name to "John"
        String name = "John";
        byte[] nameBytes = name.getBytes();
        
        for (int i = 0; i < nameBytes.length; i++) {
            memoryBlock[nameOffset + i] = nameBytes[i];
        }
        
        System.out.println("Memory block allocated and initialized.");
    }
}