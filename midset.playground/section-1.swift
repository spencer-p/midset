// A test to port dot.c into Swift and OOP

import UIKit

class Dot {
    
    init(side: Dot.Side, xSteps: Double, yard: Double, ySteps: Double, yReference: Dot.UpDownReference) {
        self.side = side
        self.xSteps = xSteps
        self.yard = yard
        self.ySteps = ySteps
        self.yReference = yReference
    }
    
    init (x: Double, y: Double) {
        self.x = x
        self.y = y
    }
    
    //Traditional form data
    enum Side: Int {
        case one = 1
        case two
    }
    
    enum UpDownReference: Int {
        case frontSideline = 1;
        case frontHash, backHash, backSideline
    }
    
    
    //Positive step values go towards origin, negative away
    var side: Side? = nil
    var yard = 0.0
    var xSteps = 0.0
    var yReference: UpDownReference? = nil
    var ySteps = 0.0
    
    // (x, y) component form as calculated properties
    var x: Double {
        get {
            var x = (-8.0*(self.yard as Double/5.0)+80.0) - self.xSteps
            if self.side == Dot.Side.one {
                x *= -1
            }
            return x;
        }
        set {
            //Get the yardage
            self.yard = 50 - (floor(abs(newValue)/8)*5)
            if abs(newValue).truncatingRemainder(dividingBy: 8) > 4 { //More than 4 steps from a yard means the reference is the other yardline
                self.yard -= 5
            }
            
            //get steps
            self.xSteps = newValue //+(8*((50-self.yard)/5)))
            if (newValue < 0) {
                self.side = Dot.Side.one
                self.xSteps += 8*((50-self.yard)/5)
            }
            else {
                self.side = Dot.Side.two
                self.xSteps -= 8*((50-self.yard)/5)
            }
        }
    }
    var y: Double {
        get {
            switch self.yReference! {
            case Dot.UpDownReference.frontSideline:
                return self.ySteps
            case Dot.UpDownReference.backSideline:
                return 84+self.ySteps
            case Dot.UpDownReference.frontHash:
                return 28+self.ySteps
            case Dot.UpDownReference.backHash:
                return 56+self.ySteps
            }
        }
        set {
            if newValue < 14 { // 14 is halfway from sideline to hash
                self.yReference = Dot.UpDownReference.frontSideline
                self.ySteps = newValue
            }
            else if newValue < 42 { // halfway from front hash to back hash
                self.yReference = Dot.UpDownReference.frontHash
                self.ySteps = newValue - 28
            }
            else if newValue < 70 { // halfway from back hash to sideline
                self.yReference = Dot.UpDownReference.backHash
                self.ySteps = newValue - 56
            }
            else {
                self.yReference = Dot.UpDownReference.backSideline
                self.ySteps = newValue - 84
            }
        }
    }
    
    func midset(next: Dot) -> Dot {
        return Dot(x: (self.x+next.x)/2, y: (self.y+next.y)/2)
    }
    
    var description: String {
        get {
            
            var desc = "Side \(self.side!.rawValue): "
            
            if self.xSteps > 0 {
                desc += "\(self.xSteps) outside "
            }
            else if self.xSteps < 0 {
                desc += "\(abs(self.xSteps)) inside "
            }
            else {
                desc += "On "
            }
            
            desc += "the \(self.yard) yardline\t"
            
            if self.ySteps < 0 {
                desc += "\(abs(self.ySteps)) in frnt of "
            }
            else if self.ySteps > 0 {
                desc += "\(self.ySteps) behind "
            }
            else {
                desc += "On "
            }
            
            switch self.yReference! {
            case .frontSideline:
                desc += "front sideline"
            case .backSideline:
                desc += "back sideline"
            case .frontHash:
                desc += "front hash"
            case .backHash:
                desc += "back hash"
            }
            
            return desc
        }
    }
}

var one = Dot(side: .one, xSteps: 0, yard: 0, ySteps: 0, yReference: .frontSideline)
var two = Dot(side: .two, xSteps: 0, yard: 15, ySteps: 0, yReference: .backSideline)

print(one.midset(next: two).description)
