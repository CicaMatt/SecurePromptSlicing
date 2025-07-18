public int getArrayIndexValue(int[] arr, int index) {
        // Check if the index is within bounds of the array
        if (index >= 0 && index < arr.length) {
            return arr[index];
        } else {
            throw new IndexOutOfBoundsException("Invalid Index: " + String.valueOf(index));
        }
    }