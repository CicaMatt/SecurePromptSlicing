class Person {
    int age;
    String name;

    public Person(int age, String name) {
        this.age = age;
        this.name = name;
    }

    @Override
    public String toString() {
        return "Person{" +
                "age=" + age +
                ", name='" + name + '\'' +
                '}';
    }
}

class MemoryAllocator {

    private Object[] memoryPool;
    private boolean[] status;

    public MemoryAllocator(int poolSize) {
        memoryPool = new Object[poolSize];
        status = new boolean[poolSize];
        for (int i = 0; i < poolSize; i++) {
            memoryPool[i] = null;
            status[i] = false;
        }
    }

    public int allocate() {
        for (int i = 0; i < status.length; i++) {
            if (!status[i]) {
                status[i] = true;
                return i;
            }
        }
        throw new OutOfMemoryError("No available memory block.");
    }

    public void deallocate(int index) {
        if (index >= 0 && index < status.length) {
            status[index] = false;
            memoryPool[index] = null;
        } else {
            throw new IndexOutOfBoundsException("Invalid memory block index: " + index);
        }
    }

    public Object getMemoryBlock(int index) {
        if (index >= 0 && index < status.length) {
            return memoryPool[index];
        } else {
            throw new IndexOutOfBoundsException("Invalid memory block index: " + index);
        }
    }

    public static void main(String[] args) {
        MemoryAllocator allocator = new MemoryAllocator(10);

        int index = allocator.allocate();
        Person person = new Person(30, "John Doe");
        allocator.memoryPool[index] = person;

        System.out.println("Allocated memory block at index: " + index);
        System.out.println("Person data: " + allocator.getMemoryBlock(index));

        allocator.deallocate(index);
        System.out.println("Deallocated memory block at index: " + index);
    }
}