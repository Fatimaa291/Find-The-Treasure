# 🗺️ Find The Treasure 💎

A console-based treasure hunting game developed in **C++** using **Object-Oriented Programming (OOP)** concepts.

## 🎮 Game Overview

The player enters their name, chooses a difficulty level, and searches through randomly generated doors to find the hidden treasure.

Each door can have a different outcome, including a treasure, trap, hint, quiz, or empty result.

## 🎯 Difficulty Levels

| Difficulty | Doors | Tries |
|------------|-------|-------|
| 🟢 Easy | 5 | 3 |
| 🟡 Medium | 8 | 4 |
| 🔴 Hard | 12 | 6 |

## 🕹️ How to Play

1. Enter your name.
2. Choose a difficulty level.
3. Select a door by entering its number.
4. Check what is behind the selected door.
5. Use hints and solve quizzes to increase your score.
6. Find the treasure before you run out of tries.

## 🚪 Door Outcomes

- 💎 **Treasure** — Earn 5 points.
- 🪤 **Trap** — Lose 2 points.
- 💡 **Hint** — Receive a clue about the treasure.
- 🧠 **Quiz** — Answer a quick math question.
- 🚪 **Empty Door** — No points are gained or lost.

## 💡 Hint System

Hints can provide clues such as:

- Try even or odd numbered doors.
- Look towards higher or lower numbered doors.
- Check whether the treasure is behind the first door.

## 🧠 Quick Quiz

Some doors trigger a quick addition quiz.

- ✅ Correct answer — **+3 points**
- ❌ Wrong answer — **0 points**
- ⏰ No answer within 3 seconds — **0 points**

## 🏆 Scoring

| Action | Points |
|--------|--------|
| 💎 Find Treasure | +5 |
| 🧠 Correct Quiz Answer | +3 |
| 🪤 Trap | -2 |
| 🚪 Empty Door | 0 |

## 📚 OOP Concepts

The project uses:

- Classes and Objects
- Constructors
- Encapsulation
- Static Members
- Dynamic Memory Allocation
- Destructors
- Factory Pattern

## 🛠️ Technologies

- C++
- Object-Oriented Programming
- Windows Console

