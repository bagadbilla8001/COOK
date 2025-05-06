import java.util.*;

public class heapsort {

    // Function to perform heapsort (ascending)
    public static void heapSort(int[] arr) {
        int n = arr.length;

        // Build max heap
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i);

        // Extract elements from heap one by one
        for (int i = n - 1; i > 0; i--) {
            // Swap root with the last element
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;

            // Heapify the reduced heap
            heapify(arr, i, 0);
        }
    }

    // To heapify a subtree rooted at index i
    public static void heapify(int[] arr, int size, int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] > arr[largest])
            largest = left;

        if (right < size && arr[right] > arr[largest])
            largest = right;

        if (largest != i) {
            int swap = arr[i];
            arr[i] = arr[largest];
            arr[largest] = swap;

            heapify(arr, size, largest);
        }
    }

    // Find min and max marks using heaps
    public static void findMinMaxMarks(int[] marks) {
        PriorityQueue<Integer> minHeap = new PriorityQueue<>();
        PriorityQueue<Integer> maxHeap = new PriorityQueue<>(Collections.reverseOrder());

        for (int mark : marks) {
            minHeap.add(mark);
            maxHeap.add(mark);
        }

        System.out.println("Minimum Marks: " + minHeap.peek());
        System.out.println("Maximum Marks: " + maxHeap.peek());
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        while (true) {
            System.out.println("\n===== Menu =====");
            System.out.println("1. Find Min and Max Marks");
            System.out.println("2. Sort Marks (Heapsort Ascending)");
            System.out.println("3. Exit");
            System.out.print("Enter your choice: ");
            int choice = scanner.nextInt();

            if (choice == 3) {
                System.out.println("Exiting...");
                break;
            }

            System.out.print("Enter number of students: ");
            int n = scanner.nextInt();
            int[] marks = new int[n];

            System.out.println("Enter marks:");
            for (int i = 0; i < n; i++) {
                marks[i] = scanner.nextInt();
            }

            switch (choice) {
                case 1:
                    findMinMaxMarks(marks);
                    break;

                case 2:
                    heapSort(marks);
                    System.out.println("Marks sorted in ascending order:");
                    for (int mark : marks) {
                        System.out.print(mark + " ");
                    }
                    System.out.println();
                    break;

                default:
                    System.out.println("Invalid choice!");
            }
        }

        scanner.close();
    }
}
/*===== Menu =====
1. Find Min and Max Marks
2. Sort Marks (Heapsort Ascending)
3. Exit
Enter your choice: 1
Enter number of students: 5
Enter marks:
75 90 60 85 50

===== Menu =====
1. Find Min and Max Marks
2. Sort Marks (Heapsort Ascending)
3. Exit
Enter your choice: 2
Enter number of students: 5
Enter marks:
75 90 60 85 50

===== Menu =====
1. Find Min and Max Marks
2. Sort Marks (Heapsort Ascending)
3. Exit
Enter your choice: 3
 */