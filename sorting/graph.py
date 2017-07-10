
import matplotlib.pyplot as plt

sizes = [ [100, 1000, 10000, 100000], 
		  [100, 1000, 10000, 100000, 1000000, 10000000],
		  [100, 1000, 10000, 100000, 1000000, 10000000, 100000000] ]


data = {}
data['insertion'] = [[0.002, 0.156, 14.517, 1401.88],sizes[0],'Insertion sort','r']
data['selection'] = [[0.007, 0.362, 27.731, 2729.8],sizes[0],'Selection sort','g']
data['stable_selection'] = [[0.008, 0.43, 36.768, 3675.41],sizes[0],'Stable selection sort','b']
data['heap'] = [[0.005, 0.057, 0.676, 10.375, 130.348, 2186.05],sizes[1],'Heap sort','c']
data['merge'] = [[0.006, 0.061, 0.705, 10.883, 126.369, 1257.12],sizes[1],'Merge sort','m']
data['ite_merge'] = [[0.004,0.054, 0.655, 9.773, 125.564, 1309.06, 14961.7],sizes[2],'Iterative merge sort','y']
data['lomuto'] = [[0.004, 0.06, 0.554, 7.753, 84.433, 806.017, 9090.41],sizes[2],'Lomuto quicksort','r']
data['hoare'] = [[0.004, 0.04, 0.481, 7.017, 92.214, 861.419, 9804.79],sizes[2],'Hoare quicksort','g']
data['yaroslavskiy'] = [[0.003, 0.037, 0.45, 6.631, 80.291, 761.541, 8763.43],sizes[2],'Yaroslavskiy quicksort','k']

fig, ax = plt.subplots()

for key in data :
	ax.loglog( data[key][1], data[key][0], label=data[key][2], basex=10, color=data[key][3] )

legend = ax.legend( loc='lower right', shadow=True )

plt.show()
