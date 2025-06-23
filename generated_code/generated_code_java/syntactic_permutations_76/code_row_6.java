public class Person {
    public int status = 0;
}

class MemoryAllocator {
    private static int bytesPerPerson = 4 * 1024;
    private byte[] memoryPool;
    private List<Integer> freeBlocks;

    public MemoryAllocator(int totalBytes) {
        this.memoryPool = new byte[totalBytes];
        this.freeBlocks = new ArrayList<>();
        for (int i = 0; i < totalBytes / bytesPerPerson; i++) {
            freeBlocks.add(i);
        }
    }

    public Person allocate() {
        if (freeBlocks.isEmpty()) {
            return null;
        }
        int index = freeBlocks.remove(0);
        return new Person();
    }
}