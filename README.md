# Mini Project OOP – Asteroid Resource Mining 🚀

**Author:** Cătălin Gabriel Badea  
**Group:** 322AB  

---

## 📌 Overview

This is a homework developed for an Object-Oriented Programming (OOP) assignment at university.  
The goal was to simulate a mission of mining resources from asteroids using rockets, each with its own characteristics and operational costs.  

The program reads input files describing rockets, asteroids, and market prices, then calculates missions that maximize profit by optimizing resource extraction and fuel consumption.  

This is a small educational project designed to demonstrate my coding style, clarity, and how I apply OOP concepts, rather than a fully polished product.

---

## 🎯 Assignment Requirements

- Reading input files (`rachete.csv`, `asteroizi.csv`, `piata.csv`) containing information about rockets, asteroids, and resource prices.  
- Implementing classes such as **Resource**, **Rocket**, **Asteroid**, and **Mission** to model the data and logic.  
- Calculating mission parameters: extracted quantity, fuel consumption, fuel cost, gross profit, and net profit.  
- Generating output CSV files with mission details, total profits per rocket, profit per resource, and rocket rankings by efficiency.  
- Running the program from the command line with the three CSV files as arguments.  
- Avoiding STL containers for better understanding of manual memory management and data structures.

---

## 🛠️ Implementation Details

- Created classes **Resource**, **Rocket**, **Asteroid**, and **Mission** to organize data and behavior.  
- In **main()**, implemented the logic that iterates over asteroids and rockets to find the most profitable mining missions.  
- Used a `simulateMission` function to estimate profits before committing to a mission, and `executeMission` to update resources and stocks.  
- Two main approaches were attempted for mission selection:  
  - A heuristic method that sorts asteroids by distance and rockets by efficiency, trying to use the best rocket first.  
  - A brute force method checking all possible rockets for each asteroid to find the highest profit mission.  
- Generated detailed CSV reports according to the project specification.

---

## 📂 Output Files

- **misiuni.csv** — details of each mission including rocket used, asteroid mined, resources extracted, fuel consumption, and profits.  
- **profit_total.csv** — total gross and net profits per rocket.  
- **profit_resursa.csv** — gross profit and total quantity extracted per resource.  
- **clasament_rachete.csv** — rocket ranking by net profit and efficiency score.

---

## ⚠️ Notes

- This project is primarily educational, meant to demonstrate OOP design and basic resource management logic.  
- Some edge cases, especially with very large datasets, are not fully optimized.  
- Memory management is done manually without STL containers as per assignment constraints.

---

## 💬 Acknowledgments

Thank you for your interest!  
Feel free to ask any questions or provide suggestions.

---

*— Cătălin Gabriel Badea*

