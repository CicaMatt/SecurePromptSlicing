id_sequence = ['A12345678', 'B09876543', 'C12987346']
      def get_id(index):
        return id_sequence[index]
      print("Enter the index value:")
      inp = int(input())
      print(get_id(inp))