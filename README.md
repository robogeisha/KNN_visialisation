# KNN_visualizer

The predictSpotSafety function takes the current mouse position and calculates the Euclidean distance
to each spot in the spots array.

Spots within a distance of 50 from the mouse position are deemed as "neighbors" and thus, considered "unsafe". 
This is represented by colorScheme[1].

Spots that are further away (distance >= 50) are not considered neighbors and are deemed "safe", 
represented by colorScheme[0].

The function then checks if there are more "safe" spots than "unsafe" ones. 
If there are, it returns true, indicating that the current mouse position is in a "safe" zone. 

If there are more "unsafe" spots, it returns false, indicating that the current mouse position is in an "unsafe" zone.

