# Global_alignment

This project is based on repository [Globally_Aligned_Events
](https://github.com/Haram-kim/Globally_Aligned_Events).

I only did some slight changes in order to complete the need of my master thesis.
Please refer to the original repository for detailed information on prerequisites.
Here I list the main modifications I have made:
- replace all uint16 data type with uint32 in order to avoid overflow when using more intensive datasets
- output the estimated pose to txt file for further comparison and evaluation
  - output format: time x y z q_x q_y q_z q_w
- set publisher/receiver queue size to inf
- add configuration files to support ESIM datasets and (shapes_rotation/boxes_rotation/dynamic_rotation/poster_rotattion).
- skip event_bundler. now events from event_publisher go directly to rotation_estimator
- delete code that is not used in my thesis
