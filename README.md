# Be The Controller

## Synopsis

The primary goal of the Be the Controller tool kit is to help game designers easily identify and recognise a user’s pose and gestures using a motion controller, in order to then link these movements with actions in a game. This software library provides the developer with the infrastructure to load lists of poses and gestures to an application, which are then recognised and linked to the appropriate action

The tool uses a “skeletal relation angle recognition method” rather than the most common “body parts Cartesian co-ordinates position recognition method”, which provides a more flexible and accurate way to create and recognise poses and gestures. By using this method, the tool can recognise poses unaffected by the positioning of the body’s parts in the virtual world environment because it only compares the relationship of the parts, (if the positioning of two parts changes but they keep the same angle/relation between them they will still be recognised as the previous pose).

Furthermore, the tool achieved high performance by restricting the comparison to the active relations of poses and by simplifying gestures as a sequence of two poses instead of representing them as a set of continuous changes of the tracked relations.


## Developers Note

The project was developed using NetBeans IDE and virtual folders were used to group code files. For this reason, it is better to use NetBeans for developing on this project in order to be able to see the structure of the code.

## License

The BTC project is licensed under LGPL version 3 (also known as LGPLv3). 

