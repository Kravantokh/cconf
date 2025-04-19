# cconf

This is a simple C program made to ease the management and deployment of my parametric system configuration (on archlinux).

## Disclaimer

NOTE: I am not responsible for any borking/breaking/bricking of your system that may result from using this tool. Use it only at your own risk!

Currently this program is in its early stages of development. Expect potentially breaking changes and many refactorings. The project's future is also uncertain. I may decide to quit maintaining it at any moment without any announcement for now. (Not like that should stop anyone from forking and using it if they so desire)

## Parametric what?!

Parametric configurations. What I refer to by parametric configurations is the idea that sometimes one would just prefer to hide all the complexity of the configuration of some programs behind a few simple abstractions, such as feature on-off toggles or colors, to name a few. These are useful when one wants to create a configuration that can be used by multiple people, who, broadly speaking, have the same preferences but would still like some further customizability. In simple terms, suppose, for example, that I have a decent configuration for `yambar` which I would like to use both on my laptop and desktop system. On my laptop I would like to have battery level and monitor luminosity adjustment in the statusbar. On my desktop system, much less so. As such, these features should be toggleable in the configuration. In a sense, the configurations built here are somewhat generic and allow for toggling a few such simple features on and off.

## Short history

Over the years I have had several system configuration and some attempts at trying to make their deployment and management simple. But at some point a few friends also started using my configuration and their different preferences led to this whole idea of having the configuration be parametric in some ways. At the very least the main colors of the theme had to be changeable besides the wallpaper. So at first I came up with a hacky solution that used `sed` to create a rather primitive preprocessor. This was my first implementation of this idea of parametric configurations. But that system proved too clunky to use over time. It did do its job, the colors could be changed in a central place and every program (notification daemon, status bar, launcher etc) in the configuration would switch its colors accordingly after running the processing step and updating their configuration files. This left me with one further problem, however: **package management**. In this version I think I have tackled the problem with the help of pacman (and yay).

## Why C?

C is a great language.

C is strongly typed. Which means that we can use the compiler to make sure that the configuration options' datatypes are respected (for the most part). Moreover, the user of a configuration can see exactly what parameters can be adjusted and what types they are expected to be.

Well, that applies to a lot of other languages. The real reason is that C is ubiquitous. You are hard pressed to find a linux system without a C compiler already on it, hence I am not forcing anyone to needlessly fill their system with bloated software only to be able to run this configurator. Besides, I just like using C.

## Compatibility notes

This system was built for archlinux. It relies on `yay` (or any other AUR manager symlinked or aliased to yay) to manage the system packages, as such it will not run on any other distributions, although conceivably it could be ported to other distributions as well.

## Examples

Check the `configurations` directory for examples.

## Usage

Make sure you have a file named `configuration.c`. I'd recommend that you copy (or symlink) one of the examples to `configuration.c` as a starting example.

NOTE: Use this program at your own risk.

