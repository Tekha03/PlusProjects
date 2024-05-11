import random

rock = '''
    _______
---'   ____)
      (_____)
      (_____)
      (____)
---.__(___)'''

paper = '''
     _______
---'    ____)____
           ______)
          _______)
         _______)
---.__________)
'''

scissors = '''
    _______
---'   ____)____
          ______)
       __________)
      (____)
---.__(___)
'''

rock_paper_scissors = [rock, paper, scissors]

print("Welcome to the Rock-Paper-Scissors Game!")
gamer_choice = int(input("What do you choose? Type 0 for Rock, 1 for Paper and 2 for Scissors.\n"))
if gamer_choice > 2 or gamer_choice < 0:
    print("You typed an invalid number, you lose.")
    exit()
print(rock_paper_scissors[gamer_choice])

computer_choice = random.randint(0, 2)
print("Computer choice:")
print(rock_paper_scissors[computer_choice])
row1 = [2, 0, 1]
row2 = [1, 2, 0]
row3 = [0, 1, 2]
game_table = [row1, row2, row3]

outcome = game_table[gamer_choice][computer_choice]
if outcome == 0:
    print("\nYou lose(((")
elif outcome == 1:
    print("\nYou win!")
else:
    print("\nDraw.")