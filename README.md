# 🧠 SYNAPSE

### Switch-Controlled Yoked Navigated & Adaptive Prosthetic Support Equipment

**Smart India Hackathon 2025 | Team BRAINI-X | Problem ID: SIH25148**

---

## 📌 Overview

SYNAPSE is a low-cost, switch-controlled wrist–hand orthosis designed to assist individuals with upper-limb weakness caused by stroke and neurological disorders.

The system enables **assisted grasp–hold–release functionality** using a deterministic three-state control interface, servo-driven cable actuation, and embedded finite state machine (FSM) logic implemented on ESP32.

Unlike complex EMG-based or multi-DOF exoskeleton systems, SYNAPSE prioritizes:

* ✅ Simplicity
* ✅ Safety
* ✅ Affordability
* ✅ Deterministic Control
* ✅ Real-time Embedded Implementation

---

## 🎯 Problem Statement

**Dextra: Switch-controlled wrist-hand orthosis for enhanced functional independence**

A significant percentage of stroke survivors experience permanent upper-limb weakness. Existing rehabilitation devices are:

* Expensive
* Mechanically complex
* Difficult to operate
* Inaccessible in low-resource regions

SYNAPSE addresses this gap with a minimal, user-friendly assistive device.

---

## 🏗️ System Architecture

### 🔁 Control Flow

```
User → 3-State Switch → ESP32 (FSM) → PWM Output → Servo Motor
→ Cable Mechanism → Assisted Hand Motion
```

---

## ⚙️ Hardware Components

* **Microcontroller:** ESP32 (RTOS capable)
* **Actuator:** Metal Gear Servo Motor
* **Mechanism:** Cable-driven tendon system
* **Force Feedback:** Strain gauge (adaptive grip control)
* **Structure:** 3D printed enclosure
* **Weight Target:** ≤ 800 g
* **Response Time:** ≤ 300 ms

---

## 🧠 Control Logic

### 3-State Switch Interface

| State | Function |
| ----- | -------- |
| 0     | Neutral  |
| 1     | Grasp    |
| 2     | Release  |

The ESP32 runs a **Finite State Machine (FSM)** that:

* Maps switch state to predefined servo positions
* Enforces motion limits
* Maintains stable grasp
* Prevents unintended release
* Ensures safe physiological boundaries

---

## 🔒 Safety & Constraints

* Servo torque limits enforced via firmware
* Motion range restricted mechanically + via PWM limits
* Configurable grip force threshold
* Closed-loop feedback prevents excessive force

---

## 📲 Smart Features

* ESP32 wireless capability (BLE/WiFi)
* Real-time monitoring
* Dual modes:

  * Daily Assist Mode
  * Rehabilitation Training Mode
* AI-based rehabilitation tracking (TinyML integration)
* Automated report generation (Python backend)

---

## 📊 Impact

* 1.29 million new stroke cases annually in India
* 70–80% survivors suffer upper limb disability
* 70–80% cheaper than traditional orthotic systems
* Potential to restore functional grasp for ~170,000 individuals/year (with 10% adoption)

---

## 🛠️ Technologies Used

* Embedded C
* ESP-IDF
* Finite State Machine Architecture
* PWM Motor Control
* Cable-driven Mechanical Actuation
* TinyML (Rehabilitation tracking)
* Android Studio (IoT App)
* Python (Report automation)

---

## 🔬 Research Foundation

Built referencing:

* Development of Powered Upper Limb Orthosis for Muscular Weakness
* Design of Portable Hand Exoskeleton with Bowden Cable Mechanism

---

## 👩‍💻 Team BRAINI-X

* Mayur V (Team Guide)
* Dhanush S (Team Lead) 
* Kaver S A
* Anagha N G
* Koushikh Gowda S M
* Harshith 
* Usha S gowda
  
---

## 🚀 Future Improvements

* Multi-finger proportional force control
* Adaptive grip classification
* Clinical pilot testing
* Lightweight custom PCB design
