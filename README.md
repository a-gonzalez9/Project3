Team Name: The Fridgeneers
Team Members: Angelina Gonzalez, Carmel Norris, Ramia Ambreen
Project Title: Fridge

Problem: Our goal is to address the issue of meal planning with the limited number of ingredients at hand. Many people find it difficult to decide what to cook, particularly when they have dietary restrictions or certain ingredients are missing. Our project offers personalized recipe suggestions according to the user's preferences, dietary requirements, and time constraints, as well as the ingredients they have on hand.

Motivation: This is a common issue for many households that have trouble organizing their meals, especially when time is tight or grocery shopping is less frequent. For busy people or those with dietary restrictions, an intelligent meal recommendation system could significantly impact how much food is wasted, increase efficient use of time, and help those with diet restrictions.

Features: We will know the problem is solved when the system can offer recipe suggestions based on ingredients that are readily available, let users sort recipes by calorie count, cooking time, allergens, etc., modify ingredient amounts according to the number of guests being served, take user preferences into account for tailored recommendations, and guarantee flexibility in recipe filtering based on available kitchen equipment or skill levels.

Data:
Food.com Recipes and Interactions: https://www.kaggle.com/datasets/shuyangli94/food-com-recipes-and-user-interactions 

Tools: C++ will be used as the programming language and SFML will be used to build the interface and handle user interaction.

Visuals: Wireframes/Sketches of the interface or the menu driven program
Home Page
Results Page

Strategy: We will use a greedy search algorithm in order to find the best match recipes based on ingredient overlap, as well as hash maps to store recipe data and efficiently match available ingredients with recipes. Binary search trees will ensure fast sorting and filtering by quantitative attributes. We will compare heaps and hash maps in this project, as they both are equally capable of handling this task and could make good comparisons. 
// Make sure you display the results of your comparison, so for example you could do the calculations twice with heaps and then hash maps and display somewhere "It took heaps __ seconds to find you recipes vs __ seconds for hash maps" or you could ask the user each time if they want to use heaps or hash maps and only display the time for using that data structure <= comment from TA

Distribution of Responsibilities and Roles:  Carmel will focus primarily on the backend code by implementing algorithms and logic using C++, Ramia will focus primarily on the frontend code by using SFML to develop the interface, and Angelina will focus on a mix of both roles.

References: 

https://www.kaggle.com/datasets/shuyangli94/food-com-recipes-and-user-interactions

https://www.sfml-dev.org/ 

https://www.geeksforgeeks.org/how-to-use-hashmap-in-cpp/# 
