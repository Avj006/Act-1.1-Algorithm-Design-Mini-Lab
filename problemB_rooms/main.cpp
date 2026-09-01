#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;
/*
//Auxiliary Heap Operations Pseudocode -> done automatically by the C++ heap (yet just for visualization purposes)

#1 - Function Heap_Pop(heap_array):

1. Take the value of the last leaf of the HEAP, that is, the last element of the array.
 	root_value = heap_array[0]
    	last_index = heap_array.length - 1
    	last_leaf_value = heap_array[last_index]
2. Swap this value with the one at the root.
   	heap_array[0] = last_leaf_value
3. Physically eliminate the node that represents the last leaf.
    	heap_array.remove_at(last_index)
4. Finally, reorder downwards the element that remained as the root of the HEAP:
    	current = 0
    	while ((current * 2) + 1) < heap_array.length:
4.1. Compare the value of the node with the child nodes.
       	left_child = (current * 2) + 1
        	right_child = (current * 2) + 2
        	highest_priority_child = left_child
        	if (right_child < heap_array.length and heap_array[right_child] > 
priority than heap_array[left_child]):
            		highest_priority_child = right_child
4.1.1. If the value of the parent has a higher priority, the reordering process ends here.
        	if (heap_array[current] >= priority than 
 	heap_array[highest_priority_child]):
            		break

4.1.2. If the value of any child has a higher priority, swap this with the parent, and repeat the downward reordering process with the children of the swapped element.
        	swap(heap_array[current], heap_array[highest_priority_child])
        	current = highest_priority_child
    	return root_value


#2 - Function Heap_Push(heap_array, new_element):

1. Insert the new element as the last leaf of the HEAP, that is, as the last element of the array.
heap_array.append(new_element)
    	current = heap_array.length - 1

2. Compare this new element with respect to its parent; if the element was inserted at position k, the parent will be at position k/2.
    // Adjusted for 0-index: parent is at (k-1)/2
    	while (current > 0):
        	parent = (current - 1) / 2

3. If the value of the parent has a lower priority, swap them and continue comparing upwards.
        	if (heap_array[parent] < priority than heap_array[current]):
            		swap(heap_array[parent], heap_array[current])
            		current = parent

4. If the value of the parent has a higher priority, the process ends there.
        	else:
            		break
 */
vector<pair<int, int>> meetings_v;
int main(){
    /*
    1. Recieve number. Save it as m, which represents the total number of meetings.
	m = input
    */
    int m;
    if (!(cin >> m)) return 0;
    /*
    2. Recieve 2 numbers spearated by a space (loop for as many meetings) + validate with m.
	meetings_v = empty_list() for a lenght m: start, end = read_two_integers()
    3. Store pairs in vectormeetings_v.append((start, end))
    */
   for (int i = 0; i < m; i++) {
        pair<int, int> meetingSchedule;
        cin >> meetingSchedule.first >> meetingSchedule.second;
        meetings_v.push_back(meetingSchedule);
    }
    /*
    4. Sort (ascending meetings' start times) sort(meetings_v, based_on = start_time)
    */
    sort(meetings_v.begin(), meetings_v.end());
	/*
	5. Initialize Min Heap min_heap = empty_array()
	*/
	priority_queue<int, vector<int>, greater<int>> rooms_heap; //min-heap in c++
	/*
	6. Loop: to iterate through vector for meetings. For each meeting, look at the root of 
	the Min Heap (room that has a vacancy the earliest). for current_meeting in meetings_v:
	*/
	for (int i=0; i < m; i++){
		/*
		6.1. If this room's end time is less than or equal to the current meeting's start time, 
		the room is vacant. Pop it from the heap.if (min_heap.length > 0) and (min_heap[0] <= 
		current_meeting.start): Heap_Pop(min_heap)
		*/
		if (!rooms_heap.empty() && rooms_heap.top() <= meetings_v[i].first) {
			rooms_heap.pop();
		}
		/*
		6.2. Insert (push) the current meeting's ending time into the Min Heap. This signifies that 
		a room (recycled one/new one) is now occupied. Heap_Push(min_heap, current_meeting.end)
		*/
		rooms_heap.push(meetings_v[i].second);
		/*
		7. End of loop. Min heap -> has total number of rooms needed (minimum). Return size/number of
		elemnts in the heap. return min_heap.length
		*/
	}
	cout<<rooms_heap.size()<<endl;
};